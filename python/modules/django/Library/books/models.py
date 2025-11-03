from django.db import models


# Create your models here.


# one to one relationship- each author have its own profile

class Profile(models.Model):
    bio = models.TextField()
    author = models.OneToOneField("Author",
                                  on_delete=models.CASCADE,
                                  related_name="profile")

    def __str__(self):
        return self.author.__str__()


class Author(models.Model):
    firstname = models.CharField(max_length=100)
    surname = models.CharField(max_length=100)
    birthday = models.DateField(null=True, blank=True)

    def __str__(self):
        return f"{self.firstname} {self.surname}"


# one-to-many Author and Book ( one author can have many books written )
# many-to-many Book Genre ( one book can have many genres, and one gengre can have many books)

class Genre(models.Model):
    name = models.CharField(max_length=100)

    def __str__(self):
        return self.name


# wiele ksiazek moze byc przypisanych do jednego autora
# oraz jedna ksiazka ma tylko jednego autora
class Book(models.Model):
    title = models.CharField(max_length=200)
    author = models.ForeignKey(
        to=Author,
        on_delete=models.CASCADE,
        related_name="books"
    )
    genres = models.ManyToManyField(to=Genre)
    published_date = models.DateField()
    pages = models.IntegerField(null=True, blank=True)
    cover_image = models.ImageField(upload_to="covers/", null=True, blank=True)
    is_available = models.BooleanField(default=True)

    def __str__(self):
        return self.title
