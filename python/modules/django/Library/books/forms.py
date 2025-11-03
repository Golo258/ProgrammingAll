from django import forms
from .models import Book, Author, Genre, Profile
from datetime import date


class BookForm(forms.ModelForm):
    class Meta:
        model = Book
        fields = "__all__"

    def clean_title(self):
        title = self.cleaned_data.get("title")
        if len(title) < 3:
            raise forms.ValidationError("Title has to been shorter than 3 letters ")
        else:
            return title


class AuthorForm(forms.ModelForm):
    class Meta:
        model = Author
        fields = ['firstname', 'surname', 'birthday']

    def clean_birthday(self):
        birthday = self.cleaned_data.get("birthday")
        today = date.today()
        if birthday == today:
            raise forms.ValidationError("Birthdate cannot be today")

        age = today.year - birthday.year - (
                (today.month, today.day) < (birthday.month, birthday.day)
        )
        if age <= 10:
            raise forms.ValidationError("Author must be older than 10 years")

        return birthday


class GenreForm(forms.ModelForm):
    class Meta:
        model = Genre
        fields = ["name"]

class ProfileForm(forms.ModelForm):
    class Meta:
        model = Profile
        fields = ['bio', 'author']
