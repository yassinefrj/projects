from django import forms


class OfferForm(forms.Form):
    name = forms.CharField(widget=forms.TextInput(
        attrs={'class': 'form-control'}))
    amount = forms.DecimalField(widget=forms.TextInput(
        attrs={'class': 'form-control', 'type': 'number'}))
    bestOfferAmount = forms.DecimalField(widget=forms.HiddenInput())
    price = forms.DecimalField(widget=forms.HiddenInput())

    def clean(self):
        name = self.cleaned_data['name']
        amount = self.cleaned_data['amount']
        bestOfferAmount = self.cleaned_data['bestOfferAmount']
        price = self.cleaned_data['price']

        if amount <= bestOfferAmount:
            self.add_error(
                'amount', "The offer must be higher than the current best offer.")

        if amount < int(price) * 0.9:
            self.add_error(
                'amount', "The offer must be at least 90% of the price.")

        return self.cleaned_data
