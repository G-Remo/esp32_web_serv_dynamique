esp32_web_serv_dynamique

ESP32 pour servir des pages HTML, JS et CSS stockées en PSRAM sans avoir à reprogrammer.

Les fichiers restent en PSRAM : les données sont automatiquement écrasées et perdues après un redémarrage.

Il suffit de les téléverser sur l'ESP32, avec une taille maximale de 200 Ko par fichier.

Les documents ont un nom prédéfini dans le serveur :

    http://mon_ip/html_1
    http://mon_ip/html_5
    http://mon_ip/css
    http://mon_ip/js

Pour contourner l’erreur "Mixed Content : Surclassement de la requête d’affichage non sécurisée".

![upload](https://github.com/user-attachments/assets/afd76998-55ee-4743-ab30-00b1d80f7083)

![page](https://github.com/user-attachments/assets/83d68ac0-f3dc-40c9-a88f-6b9103c69367)

![mixed_content](https://github.com/user-attachments/assets/9ad0e9f1-8166-40f8-a4e9-06b5b581e134)
![page2](https://github.com/user-attachments/assets/5edaa400-bbec-4854-9bd8-d509a2fd98d8)
