from django.db import models
from django.urls import reverse
from django.contrib.postgres.fields import ArrayField


# Create your models here.


class Apartment(models.Model):
    name = models.CharField(max_length=100)
    description = models.TextField()
    disponibility = models.CharField(max_length=100)
    price = models.IntegerField()
    surface = models.IntegerField()
    terasseSurface = models.IntegerField()
    totalSurface = models.IntegerField()
    bestOfferName = models.CharField(max_length=100)
    bestOfferAmount = models.IntegerField()
    image = models.TextField()
    id = models.IntegerField(primary_key=True)

    def get_absolute_url(self):
        return reverse('odooApartment:detail', kwargs={'pk': self.pk})

    def get_offer_url(self):
        return reverse('odooApartment:offer', kwargs={'pk': self.pk})

    def __str__(self):
        return self.name

    def update_or_create_apartment(apartment_data):
        Apartment.objects.update_or_create(
            id=apartment_data["id"], defaults=apartment_data
        )

    def clear_deleted(ids_to_keep):
        Apartment.objects.exclude(id__in=ids_to_keep).delete()
