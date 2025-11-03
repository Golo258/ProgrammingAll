
from behave import when, then
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from time import sleep

@when(u'Launch Chrome Browser')
def launchBrowser(context):
    chrome_options = Options()
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--ignore-certificate-errors")
    context.driver = webdriver.Chrome(options=chrome_options)

@when(u'Open language page')
def openPage(context):
    context.driver.get("https://ux.up.krakow.pl/~grzegorz.golonka/Projekt%20/Logowanie/log_form.php")

@when(u'Enter username "{user}" and password "{password}"')
def enterInputValues(context, user, password):
    sleep(2)
    context.driver.find_element(
        By.ID, "log"
    ).send_keys(user)
    context.driver.find_element(
        By.ID, "pass"
    ).send_keys(password)

@when(u'Click on login button')
def submitLoginValues(context):
    sleep(2)
    context.driver.find_element(
        By.ID, "sub"
    ).click()


@then(u'User must go into home page')
def checkPageAndClose(context):
    sleep(2)
    header_element_content = context.driver.find_element(
        By.XPATH, "//h1[contains(text(),'Wybierz Język')]"
    ).text
    assert header_element_content == "Wybierz Język"
    context.driver.close()
