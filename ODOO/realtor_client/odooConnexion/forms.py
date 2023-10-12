import xmlrpc.client

from django import forms

from .models import OdooConnexion


class ConnexionForm(forms.ModelForm):
    class Meta:
        model = OdooConnexion
        fields = ('username', 'password', 'url', 'db')

    def clean(self):
        cleaned_data = super(ConnexionForm, self).clean()

    def login(self):
        username = self.cleaned_data.get('username')
        password = self.cleaned_data.get('password')
        url = self.cleaned_data.get('url')
        db = self.cleaned_data.get('db')

        common = xmlrpc.client.ServerProxy('{}/xmlrpc/2/common'.format(url))
        uid = common.authenticate(db, username, password, {})
        return uid
