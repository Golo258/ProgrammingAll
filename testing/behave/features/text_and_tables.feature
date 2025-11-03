Feature: Passing text and tables as parameters

  Scenario: Data processing with text and table
    Given I have some text
        """
        Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do
        eiusmod tempor incididunt ut labore et dolore magna aliqua.
        """
    And  I also have a set of specific users
      | name      | department  |
      | Barry     | Beer Cans   |
      | Pudey     | Silly Walks |
      | Two-Lumps | Silly Walks |
    When I process the text
    Then the result should be satisfactory