# tant que l’user le souhaite, recherche un appartement sur la base du nom ou de l'id ID

import xmlrpc.client
username = input('Please enter your username : ')

print(f'Your username is {username}')

choice = -1

while (choice != 'n' and choice != 'y'):
    choice = input('Do you have an API KEY ? (y-n) : ')

if (choice == 'n'):
    password = input('Please enter your password : ')
    print(f'Your password is {password}')

if (choice == 'y'):
    password = input('Please enter your api key : ')
    print(f'Your password is {password}')

db = input('Please enter your database name : ')
print(f'Your database name is {db}')

# password = '050978'
# username = '52075@etu.he2b.be'
# db = 'dev01'
url = "http://localhost:8069" #Ne change pas

try:
    common = xmlrpc.client.ServerProxy('{}/xmlrpc/2/common'.format(url))
    print("Version : ", common.version())
except Exception as e:
    print('Bad url or odoo application is off')
    s = input('PRESS ENTER TO EXIT')
    exit()

models = xmlrpc.client.ServerProxy('{}/xmlrpc/2/object'.format(url))

try:
    uid = common.authenticate(db, username, password, {})
except Exception as e:
    print('Bad database name')
    s = input('PRESS ENTER TO EXIT')
    exit()

print("uid: ", uid)

if not uid:
    print("Bad login or password")
    s = input('PRESS ENTER TO EXIT')
    exit()

choice = -1
mode = -1
while (mode != 'NAME' and mode != 'name' and mode != 'ID' and mode != 'id'):
    mode = input('Do you want to make a search with the NAME or the ID of the appartment ? (NAME/ID) : ')

try:
    while (choice != 'n' and choice != 'N'):

        if (mode == 'NAME' or mode == 'name'):
            name = input(
                'Please enter the name of the appartement you want to search for : ')
            print(f'You are searching for {name}')

            appartement = models.execute_kw(db, uid, password, 'realtor.appartement', 'search_read', [[['name', '=', name]]], {'fields': [
                                            'name', 'description', 'disponibility', 'price', 'surface', 'terasseSurface', 'totalSurface', 'bestOfferName', 'bestOfferAmount', ]})
            if(len(appartement) == 0):
                print(f'Sorry none appartment with NAME {name} found')
            else:
                print(appartement)

        if (mode == 'ID' or mode == 'id'):
                
            ID = input( 'Please enter the ID of the appartement you want to search for : ')
            int(ID)

            print(f'You are searching for appartement with ID {ID}')
            appartement = models.execute_kw(db, uid, password, 'realtor.appartement', 'search_read', [[['id', '=', ID]]], {'fields': [
                                            'name', 'description', 'disponibility', 'price', 'surface', 'terasseSurface', 'totalSurface', 'bestOfferName', 'bestOfferAmount',
                                            ]})
            
            if(len(appartement) == 0):
                print(f'Sorry none appartment with ID {ID} found')
            else :
                print(appartement)
                # Affichage de Product.quantity à partir de l'ID de l'appartement
                quantity = 0
                products = models.execute_kw(
                    db, uid, password, 'product.template', 'search_read', [[]])
                for product in products:
                    if (int(ID) == product['appartement_id'][0]):
                        quantity = product['qty_available']
                print(f'Quantité = {quantity}')

        choice = input('Do you want to continue ? (y/n) : ')

except ValueError: 
    print('You entered an incorrect value')

except Exception as e:
    print(e)

s = input('PRESS ENTER TO EXIT')
exit()