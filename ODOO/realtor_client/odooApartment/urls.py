from django.urls import path

from . import views

app_name = 'odooApartment'

urlpatterns = [
    path('home', views.home, name='home'),
    path('detail/<int:pk>/', views.apartment_detail, name='detail'),
    path('offer/<int:pk>/', views.offer, name='offer')

]
