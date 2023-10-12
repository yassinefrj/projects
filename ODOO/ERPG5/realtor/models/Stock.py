from odoo import models, fields, api


class Stock(models.Model):
    _inherit = 'stock.inventory'