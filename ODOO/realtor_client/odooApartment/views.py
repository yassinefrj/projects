import xmlrpc.client
from django.contrib.auth.decorators import login_required
from django.http import HttpResponseRedirect, HttpResponse
from django.shortcuts import render, get_object_or_404, redirect
from django.urls import reverse
from odooApartment.forms import OfferForm
from odooApartment.models import Apartment
from odooConnexion.models import OdooConnexion


@login_required
def home(request):
    connexion = OdooConnexion.objects.get(id=request.session['id'])
    models = xmlrpc.client.ServerProxy(
        '{}/xmlrpc/2/object'.format(connexion.url), allow_none=True)
    uid = connexion.connect()

    products = models.execute_kw(
        connexion.db, uid, connexion.password, 'product.template', 'search_read', [[['appartement_id', '!=', None], ['qty_available', '>=', 1]]])

    apartment_ids = [product['appartement_id'][0] for product in products]

    apartment = models.execute_kw(connexion.db, uid, connexion.password, 'realtor.appartement', 'search_read', [[['id', 'in', apartment_ids]]],
                                  {'fields': [
                                      'name', 'description', 'disponibility', 'price', 'surface', 'terasseSurface',
                                      'totalSurface', 'bestOfferName', 'bestOfferAmount', 'image']})
    for app in apartment:
        Apartment.update_or_create_apartment(app)

    apartments = Apartment.objects.all()
    Apartment.clear_deleted(apartment_ids)

    context = {
        'user': request.user,
        'id': request.session['id'],
        'apartments': apartments,
    }

    return render(request, 'odooApartment/home.html', context)


def apartment_detail(request, pk):
    connexion = OdooConnexion.objects.get(id=request.session['id'])
    models = xmlrpc.client.ServerProxy(
        '{}/xmlrpc/2/object'.format(connexion.url), allow_none=True)
    uid = connexion.connect()
    quantity = int(models.execute_kw(
        connexion.db, uid, connexion.password, 'product.template', 'search_read', [[['appartement_id', '=', pk]]])[0]['qty_available'])
    apartment = Apartment.objects.get(pk=pk)
    form = OfferForm(
        initial={'bestOfferAmount': apartment.bestOfferAmount, 'price': apartment.price})
    return render(request, 'odooApartment/detail.html', {'apartment': apartment, 'form': form, 'quantity': quantity})


def offer(request, pk):
    apartment = get_object_or_404(Apartment, pk=pk)

    if request.method == 'POST':
        form = OfferForm(request.POST)
        if form.is_valid():
            connexion = OdooConnexion.objects.get(id=request.session['id'])
            models = xmlrpc.client.ServerProxy(
                '{}/xmlrpc/2/object'.format(connexion.url))
            uid = connexion.connect()

            name = form.cleaned_data['name']
            amount = form.cleaned_data['amount']
            partner = models.execute_kw(
                connexion.db, uid, connexion.password, 'res.partner', 'search_read', [[['name', '=', name]]])
            if not partner:
                partner = models.execute_kw(connexion.db, uid, connexion.password, 'res.partner', 'create', [{
                    'name': name,
                }])
                partner_id = partner
            else:
                partner_id = partner[0]['id']

            models.execute_kw(connexion.db, uid, connexion.password, 'realtor.appartement', 'write',
                              [[apartment.id], {'bestOfferName': partner_id, 'bestOfferAmount': int(amount)}])

            return HttpResponseRedirect(reverse('odooApartment:home'))
    else:
        form = OfferForm(
            initial={'bestOfferAmount': apartment.bestOfferAmount, 'price': apartment.price})
    return render(request, 'odooApartment/detail.html', {'apartment': apartment, 'form': form})
