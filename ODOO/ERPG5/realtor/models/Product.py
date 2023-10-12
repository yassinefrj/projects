from odoo import models, fields, api


class Product(models.Model):
    _inherit = 'product.template'

    appartement_id = fields.Many2one(
        'realtor.appartement', string="Appartement", ondelete='cascade', help="Appartement")

    owner_id = fields.Many2one(
        'res.partner', ondelete='cascade', string="Propriétaire", help="Le propriétaire de l'appartement"
    )

    @api.onchange('appartement_id','name','price')
    def _onchange_appartement_id(self):
        self.price = self.appartement_id.price
        self.name = self.appartement_id.name
        self.type = 'product'
