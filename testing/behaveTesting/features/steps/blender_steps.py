from behave import given, when, then
from UtilClasses.TestedData import DataHandler


@given(u'I have a database handler')
def create_database_handler(context):
    context.db_handler = DataHandler()

@given(u'I store data with usage of {key} and value {value} in database')
def store_data_in_database(context, key, value):
    context.db_handler.insert_data(key, value)
    print(context.db_handler.data)

@when(u'I retrieve data by index: {index}')
def retrieve_data_by_index(context, index = 0):
    context.retrieved_data = context.db_handler.retrieve_data(int(index))

@then(u'I should see {displayed_data} in database')
def verify_retrieved_data(context, displayed_data):
    assert context.retrieved_data == displayed_data, \
        f"Expected data '{displayed_data}' not found in retrieved data"

