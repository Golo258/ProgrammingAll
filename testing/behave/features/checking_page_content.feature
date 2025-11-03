Feature: Show Logo

  Scenario: Logo presentation on Home Page
    Given launch chrome browser
    When  open web page
    Then  verify whether the logo presents on page
    And   close Browser



