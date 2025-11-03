Feature: Show Logo

  Background: Launch Chrome and Open Page
    Given Launch Chrome Browser
    When Open Language Page

  Scenario: Login to language project

    And  Enter username "admin" and password "admin"
    And  Click on login button
    Then User must go into home page

