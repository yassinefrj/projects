from django.contrib import messages
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User
from django.http import HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse

from odooConnexion.forms import ConnexionForm
from odooConnexion.models import OdooConnexion


def index(request):
    if request.user.is_authenticated:
        return HttpResponseRedirect(reverse('odooApartment:home'))
    else:
        context = {
            'form': ConnexionForm(),
        }
        return render(request, 'odooConnexion/index.html', context)


def log_in(request):
    if request.method == 'POST':
        form = ConnexionForm(request.POST)
        if form.is_valid():
            form.clean()
            uid = form.login()
            if uid:
                user = User.objects.filter(
                    username=form.cleaned_data['username']).first()
                if not User.objects.filter(username=form.cleaned_data['username']).exists():
                    user = User.objects.create_user(
                        username=form.cleaned_data['username'], password=form.cleaned_data['password'])
                    user.save()
                login(request, user)
                connexion = OdooConnexion.objects.filter(
                    **form.cleaned_data).first()
                if not connexion:
                    connexion = form.save()
                request.session['id'] = connexion.id
                return HttpResponseRedirect(reverse('odooApartment:home'))
            else:
                messages.error(request, 'Wrong credentials')
                return HttpResponseRedirect(reverse('odooConnexion:index'))
        else:
            messages.error(request, 'Invalid form')
            return HttpResponseRedirect(reverse('odooConnexion:index'))
    else:
        form = ConnexionForm()


def log_out(request):
    if request.user.is_authenticated:
        logout(request)
    return HttpResponseRedirect(reverse('odooConnexion:index'))
