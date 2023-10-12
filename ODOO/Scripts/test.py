import xmlrpc.client
username = "roxx"
password = "odoo"

url = "http://localhost:8069"
db = "odoo"


common = xmlrpc.client.ServerProxy(
    '{}/xmlrpc/2/common'.format(url),  allow_none=True)
# print("Version : ", common.version())

models = xmlrpc.client.ServerProxy(
    '{}/xmlrpc/2/object'.format(url), allow_none=True)
uid = common.authenticate(db, username, password, {})
# appartement = models.execute_kw(db, uid, password, 'realtor.appartement', 'search_read', [], {'fields': [
#     'name', 'description', 'disponibility', 'price', 'surface', 'terasseSurface', 'totalSurface', 'bestOfferName', 'bestOfferAmount']})
# print(appartement)

products = models.execute_kw(
    db, uid, password, 'product.template', 'search_read', [[['appartement_id', '!=', None]]])

# inventories = models.execute_kw(
#     db, uid, password, 'stock.inventory', 'search_read', [[]])

partner_ids = models.execute_kw(
    db, uid, password, 'res.partner', 'search_read', [[]])

record_id = 2

partner = models.execute_kw(
    db, uid, password, 'res.partner', 'search_read', [[['name', '=', 'Mohamed']]])


# models.execute_kw(db, uid, password, 'realtor.appartement', 'write',
#                   [[record_id], {'bestOfferName': partner}])


for product in products:
    print(product)

# for inventory in inventories:
#     print(inventory)
