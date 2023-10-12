from odoo import models, fields, api
from dateutil.relativedelta import relativedelta
from datetime import datetime


class Appartement(models.Model):
    _name = 'realtor.appartement'
    _description = 'Un appartement'

    name = fields.Char(string="Name", required=True,
                       help="Name of the Appartement")

    _sql_constraints = [
        ('field_unique',
         'UNIQUE(name)',
         'The name of the Appartement must be unique'),
    ]

    description = fields.Text(
        string="Description", required=False, help="Description of the Appartement")

    image = fields.Binary(string="Image", required=False,
                          help="Image of the Appartement")

    disponibility = fields.Datetime(string="Disponibility", required=False, help="Disponibility of the Appartement", default=(
        fields.Datetime.now() + relativedelta(months=+4)), readonly=False)

    price = fields.Float(string="Price", required=True,
                         help="Price of the Appartement", default=1)

    surface = fields.Float(string="Surface", required=True,
                           help="Surface of the Appartement",default=1)

    terasseSurface = fields.Float(
        string="Terasse Surface", required=True, help="Terasse Surface of the Appartement")

    totalSurface = fields.Float(
        string="Total Surface", help="Total Surface of the Appartement", compute='_total_surface')

    bestOfferName = fields.Many2one('res.partner', string="Best Offer Name",
                                    ondelete='cascade', help="The person who did the best offer")

    bestOfferAmount = fields.Float(
        string="Best Offer Amount", required=False, help="Best Offer for the Appartement")
        
    @api.depends('surface', 'terasseSurface')
    def _total_surface(self):
        for record in self:
            record.totalSurface = record.surface + record.terasseSurface

    @api.onchange('price')
    def _onchange_price(self):
        if self.price < 1:
            self.price = 1
            return {
                'warning': {
                    'title': "Incorrect 'price' value",
                    'message': "The price cannot be negative or null",
                },
            }
        if self.bestOfferAmount > 0 :
            self.bestOfferAmount = 0.9 * self.price

    @api.onchange('surface')
    def _onchange_surface(self):
        if self.surface < 1:
            self.surface = 1
            return {
                'warning': {
                    'title': "Incorrect 'surface' value",
                    'message': "The surface cannot be negative or null",
                },
            }

    @api.onchange('terasseSurface')
    def _onchange_terasseSurface(self):
        if self.terasseSurface < 0:
            self.terasseSurface = 0
            return {
                'warning': {
                    'title': "Incorrect 'terasse surface' value",
                    'message': "The terasse surface cannot be negative",
                },
            }
    
    @api.onchange('bestOfferName')
    def _onchange_bestOfferName(self):
        if self.bestOfferName :
            if self.bestOfferAmount < 0.9 * self.price:
                self.bestOfferAmount = 0.9 * self.price

    @api.onchange('bestOfferAmount')
    def _onchange_bestOfferAmount(self):
        if self.bestOfferName :
            if self.bestOfferAmount < 0.9 * self.price:
                self.bestOfferAmount = 0.9 * self.price
                return {
                    'warning': {
                        'title': "Incorrect 'best offer' value",
                        'message': "The best offer has to be at least 90% of the price",
                    },
                }

    @api.onchange('disponibility')
    def _onchange_disponibility(self):
        tmp = datetime.today() + relativedelta(months=+3)
        if (self.disponibility < tmp):
            self.disponibility = fields.Datetime.now() + relativedelta(months=+3)
            return {
                'warning': {
                    'title': "Attention 'Disponibility' value",
                    'message': "The Disponibility has to be at least 3 month after the date of appartement creation",
                },
            }
        