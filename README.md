Real-time COVID-19 dashboard that makes effective use of IoT concepts, NodeRED, MQTT, and ESP8266 Nodemcu.

Project Title: Combating Covid-19 with IoT

As the fight against COVID-19 continues, monitoring the pandemic’s progress has become a top priority. IoT revolution is reshaping modern healthcare systems by incorporating technological, economic, and social prospects. IoT-enabled/linked devices/applications are utilized to lower the possible spread of COVID-19 to others by early diagnosis, monitoring patients, and practicing defined protocols after patient recovery. By this project we intend to get statistics throughout the world mainly focusing on Sri Lanka.

• Keep updated database about the covid-19 details in Sri Lanka daily (Daily and Total number of new cases, number of deaths, number of recovered patients)

• Keep updated database about the global covid-19 details daily (Daily and Total number of new cases, number of deaths, number of recovered patients)

• Get the total number of Sri Lankans, foreigners who have been treated and currently on treatment in a given hospital in Sri Lanka

• Get the Covid-19 statistics (Daily and Total number of new cases, number of deaths, number of recovered patients)

Data Sources

Coronavirus COVID19 API (getpostman.com) Provides current real time situation of the COVID-19 patients reported in separate countries throughout the world. 2) https://www.hpb.health.gov.lk Provides the current real time situation of the COVID-19 patients reported in Sri Lanka.
Components

➢ Open source API: To get required data.

➢ Node-red: To design the dashboard displaying corresponding data using the received data through APIs. To work as a MQTT Publisher.

➢ MQTT Broker: To filter messages based on topic, and then distribute them to subscribers.

➢ Node MCU: To work as a MQTT subscriber. To form an access point(server) and server webpage.

➢ Mobile (Client): To get the latest information through the server webpage.

System functions and features

➢ A Node-red dashboard displaying all the intended information.

➢ A server webpage (URL) displaying all the important and relevant information
