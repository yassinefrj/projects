# Generated by Django 4.1.1 on 2022-12-22 21:42

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('odooConnexion', '0005_user'),
    ]

    operations = [
        migrations.AlterField(
            model_name='user',
            name='email',
            field=models.EmailField(max_length=254, unique=True),
        ),
    ]