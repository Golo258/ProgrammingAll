return {
	"folke/todo-comments.nvim",
	enabled = true,
	event = { "BufReadPost", "BufNewFile", "BufWritePre" },
	keys = {
		{ "<leader>ft", "<cmd>TodoTelescope<cr>" }, -- find todos
	},
	opts = {},
}
