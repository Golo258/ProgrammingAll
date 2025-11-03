from behave import given, when, then
from UtilClasses.TestedData import DataProcessor


@given(u'I have some text')
def add_converted_text(context):
    context.data_process = DataProcessor()
    text_list = context.text.strip().split()

    for i in range(0, len(text_list), 2):
        if (i + 1) < len(text_list):
            context.data_process.text_list.append({
                text_list[i]: text_list[i + 1]}
            )

@given(u'I also have a set of specific users')
def add_parse_table(context):
    for row in context.table:
        context.data_process.add_data(
            row['name'], row['department']
        )


@when(u'I process the text')
def processing_test(context):
    context.people_count = context.data_process.count_people_in_department("Silly Walks")
    context.list_count = context.data_process.count_indexes_in_text()
@then(u'the result should be satisfactory')
def step_impl(context):
    assert context.people_count == 2
    assert context.list_count == 9, f"The count is different, {context.list_count}"


