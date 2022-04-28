import time
import requests


appid = "55dd60df12ee15e744b40650b2b72ce1"
temp1 = 0
windV = 0
windD = ''
deg = 0


def get_wind_direction(deg):
    res = requests.get("http://api.openweathermap.org/data/2.5/forecast",
                       params={'id': city_id, 'units': 'metric', 'lang': 'ru', 'APPID': appid})
    data = res.json()
    deg = data['list'][3]['wind']['deg']
    l = ['С ', 'СВ', ' В', 'ЮВ', 'Ю ', 'ЮЗ', ' З', 'СЗ']
    for i in range(0, 8):
        step = 45.
        min = i * step - 45 / 2.
        max = i * step + 45 / 2.
        if i == 0 and deg > 360 - 45 / 2.:
            deg = deg - 360
        if deg >= min and deg <= max:
            global windD
            windD = l[i]
            break
    return windD


# Проверка наличия в базе информации о нужном населенном пункте
def get_city_id(s_city_name):
    try:
        res = requests.get("http://api.openweathermap.org/data/2.5/find",
                           params={'q': s_city_name, 'type': 'like', 'units': 'metric', 'lang': 'ru', 'APPID': appid})
        data = res.json()
        cities = ["{} ({})".format(d['name'], d['sys']['country'])
                  for d in data['list']]
        print("city:", cities)
        city_id = data['list'][0]['id']
        print('city_id=', city_id)
    except Exception as e:
        print("Exception (find):", e)
        pass
    assert isinstance(city_id, int)
    return city_id


# Запрос текущей погоды
def request_current_weather(city_id):
    try:
        res = requests.get("http://api.openweathermap.org/data/2.5/weather",
                           params={'id': city_id, 'units': 'metric', 'lang': 'ru', 'APPID': appid})
        data = res.json()
        print("conditions:", data['weather'][0]['description'])
        print("temp:", data['main']['temp'])
        print("temp_min:", data['main']['temp_min'])
        print("temp_max:", data['main']['temp_max'])
        print("data:", data)
    except Exception as e:
        print("Exception (weather):", e)
        pass

city_id = 501175
# Прогноз
def request_forecast(city_id):
    
    try:
        res = requests.get("http://api.openweathermap.org/data/2.5/forecast",
                           params={'id': city_id, 'units': 'metric', 'lang': 'ru', 'APPID': appid})
        data = res.json()
        print('city:', data['city']['name'], data['city']['country'])
        for i in data['list']:
            print((i['dt_txt'])[:16], '{0:+3.0f}'.format(i['main']['temp']),
                  '{0:2.0f}'.format(i['wind']['speed']) + " м/с",
                  get_wind_direction(i['wind']['deg']),
                  i['weather'][0]['description'])
        global deg
        deg = i['wind']['deg']
    except Exception as e:
        print("Exception (forecast):", e)
        pass


# city_id for SPb
city_id = 501175


import sys

if len(sys.argv) == 2:
     s_city_name = "Rostov-on-Don,RU"
     print("city:", s_city_name)
     city_id = get_city_id(s_city_name)
elif len(sys.argv) > 2:
     print('Enter name of city as one argument. For example: Petersburg,RU')
     sys.exit()
request_forecast(city_id)
