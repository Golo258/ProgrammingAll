from behave import (
    given, when, then
)
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By

@given(u'launch chrome browser')
def launchBrowser(context):
    chrome_options = Options()
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--ignore-certificate-errors")
    context.driver = webdriver.Chrome(options=chrome_options)


@when(u'open web page')
def openWebPage(context):
    context.driver.get("https://pl.bab.la/")


@then(u'verify whether the logo presents on page')
def verifyLogo(context):
    status = context.driver.find_element(
        By.XPATH, "//span[@class='babla-logo']"
    )
    print(f"{status=} ")
    assert status is not None


@then(u'close Browser')
def closeBrowser(context):
    context.driver.close()

# https://ux.up.krakow.pl/~grzegorz.golonka/Projekt%20/Logowanie/log_form.php