# -*- coding: utf-8 -*-
{
    'name': "Realtor",

    'summary': """
        Realtor application""",

    'description': """
        Long description of module's purpose
    """,

    'author': "My Company",
    'website': "http://www.yourcompany.com",

    # Categories can be used to filter modules in modules listing
    # Check https://github.com/odoo/odoo/blob/14.0/odoo/addons/base/data/ir_module_category_data.xml
    # for the full list
    'category': 'Uncategorized',
    'version': '0.1',

    # any module necessary for this one to work correctly
    'depends': ['base','stock'],

    # always loaded
    'data': [
        'security/ir.model.access.csv',
        'views/appartement_view.xml',
        'views/appartement_menu_view.xml',
        'views/product_template_view.xml',
        'views/product_template_menu_view.xml',
        'views/membre_view.xml',
        'views/membre_menu_view.xml',
        'demo/demo.xml',
    ],

    'application': True,
}
