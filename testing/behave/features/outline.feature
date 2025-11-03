Feature: Outline blender checking

  Scenario Outline: Display all data in the database
    Given I have a database handler
    And  I store data with usage of <key> and value <value> in database
    When I retrieve data by index: <index>
    Then I should see <displayed_data> in database

    Examples:
      | key   | value            |  index  |  displayed_data          |
      | name  | John             |    0    |  name: John              |
      | age   | 30               |    0    |  age: 30                 |
      | email | john@example.com |    0    |  email: john@example.com |