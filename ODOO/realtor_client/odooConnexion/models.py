import xmlrpc.client

from django.contrib.auth.models import AbstractUser
from django.db import models


class OdooConnexion(models.Model):
    username = models.CharField(max_length=100, verbose_name='Name')
    password = models.CharField(
        max_length=100, verbose_name='Password or API key')
    url = models.CharField(max_length=100, verbose_name='URL')
    db = models.CharField(max_length=100, verbose_name='Datebase Name')

    def __str__(self):
        return self.username

    def connect(self):
        common = xmlrpc.client.ServerProxy(
            '{}/xmlrpc/2/common'.format(self.url))
        uid = common.authenticate(self.db, self.username, self.password, {})
        return uid
