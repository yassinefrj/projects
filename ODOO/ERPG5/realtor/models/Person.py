from odoo import fields, models


class Person(models.Model):
    _inherit = 'res.partner'

    myOffer = fields.One2many('realtor.appartement',
                              'bestOfferName', readonly=True, string="Mes Offres")
