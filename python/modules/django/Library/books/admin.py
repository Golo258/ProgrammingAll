from django.contrib import admin
from .models import (Book,
                     Author,
                     Profile,
                     Genre)
from .forms import (BookForm,
                    AuthorForm,
                    ProfileForm,
                    GenreForm)


@admin.register(Book)
class BookAdmin(admin.ModelAdmin):
    form = BookForm
    list_display = ('title','author', 'published_date','pages')
    search_fields = ('title', 'author__firstname', "author__surname")
    list_filter = ("published_date", "author",)


@admin.register(Author)
class AuthorAdmin(admin.ModelAdmin):
    form = AuthorForm
    list_display = ('firstname', 'surname', 'birthday')
    search_fields = ('firstname', 'surname')
    list_filter = ('birthday',)

@admin.register(Genre)
class GenreAdmin(admin.ModelAdmin):
    form = GenreForm
    list_display = ('name',)
    search_fields = ('name',)

@admin.register(Profile)
class ProfileAdmin(admin.ModelAdmin):
    form = ProfileForm
    list_display = ('bio', 'author')
    search_fields = ('bio', 'author__firstname', 'author__surname')
    list_filter = ('author',)