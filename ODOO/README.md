# Guide partie ODOO

## Page de première connexion ODOO
1. Pour installer les images postgres 13 et odoo 14 executer la commande suivantes (WINDOWS):

```bash
docker run -d -e POSTGRES_USER=odoo -e POSTGRES_PASSWORD=odoo -e POSTGRES_DB=postgres --name db postgres:13

docker run -v Chemin_Parent_/52075-54381/ERPG5:/mnt/extra-addons -p 8069:8069 --name odoo --link db:db -t odoo:14
```

2. Cliquer [ici](http://localhost:8069)

3. Compléter uniquement les champs :
* Database Name
* Email
* Password
* Country

4. cliquer sur "create database" sans cocher "Demo data" !

## Utilisation Module

Installer le module "Realtor"

# Guide Script

Pour utiliser le script exécuter la commande suivante (WINDOWS):

```bash
.\Scripts\vmlrpc.py
```

# Guide partie Django
## Connexion
0. Les Containers db & odoo doivent être démarrés

1. Pour lancer le serveur Django, exécuter la commande suivante (WINDOWS) :

```python
python .\realtor_client\manage.py runserver
```

2. Cliquer [ici](http://127.0.0.1:8000/)

3. Compléter les champs
* Name avec l'email choisi dans la "Page de première connexion ODOO"
* Password or API key avec le mot de passe choisi dans la " Page de première connexion ODOO " ou avec une api key crée dans odoo (Administrator -> Preferences -> Account Security -> New API KEY -> donner un nom -> Generate Key)
* URL avec http://localhost:8069
* Datebase Name avec le nom de la Datebase Name choisi dans la "Page de première connexion ODOO "
4. Cliquer sur Login

## Page HOME
La liste des appartements disponibles à la vente (étant dans un stock et avec une quantité supérieur à 0) sont affichés.

Pour voir davantage de détails sur un appartement cliquer sur "Views details"

## Page DETAILS
Pour effectuer effectuer une offre encoder
* Le nom de l'acheteur (existant ou non)
* Un montant supérieure à l'offre déjà existante


# Remerciements

Merci pour 
* La lecture
* Le temps accordé
* Les réponses aux différentes questions
