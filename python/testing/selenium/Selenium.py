
from selenium import webdriver
from selenium.webdriver.common.by import By


# otwieranie strony
driver = webdriver.Chrome()

# lokalizowanie elementów 
elementById = driver.find_element(By.ID, "id_elementu")
elementByClass = driver.find_element(By.CLASS_NAME)
elementByXpath = driver.find_element(By.XPATH)

#Operacje

elementById.click()
elementById.send_keys("Entered text") # wprowadzanie tekstu do inputa
driver.execute_script(
    "window.scrollTo(0, document.body.scrollHeight);"
)
text = elementById.text # pobieranie kontentu elementu
visibility = elementById.is_displayed()