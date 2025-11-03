defmodule Models.TaskModel do
  defstruct [:id, :title, :description, :status]


  def new(id, title, description, status \\ :incomplete) do
    if valid_title?(title) and valid_description?(description) and valid_status?(status) do
      %Models.TaskModel{
        id: id,
        title: title,
        description: description,
        status: status
      }
    else
      raise("Inappropriate data given #{title} | #{description}")
    end
  end



  defp valid_title?(title) do
    is_binary(title) and byte_size(title) > 0
  end

  defp valid_description?(description) do
    is_binary(description) and byte_size(description) > 5
  end

  defp valid_status?(status) do
    status in [:incomplete, :complete, :pending]
  end

end
