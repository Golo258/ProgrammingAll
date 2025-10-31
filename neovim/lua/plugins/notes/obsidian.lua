return {
	"epwalsh/obsidian.nvim",
	version = "*",
	lazy = false,
	ft = "markdown",
	dependencies = {
		"nvim-lua/plenary.nvim",
	},
	opts = {
		workspaces = {
			{
				name = "notes",
				path = "~/ObsidianVault",
			},
		},
		daily_notes = {
			folder = "daily",
			date_format = "%Y-%m-%d",
			alias_format = "%B %-d, %Y",
			template = nil,
		},
		completion = {
			nvim_cmp = true,
			min_chars = 2,
		},
	},
	keys = {
		{ "<leader>on", "<cmd>ObsidianNew<cr>", desc = "New Obsidian note" },
		{ "<leader>ot", "<cmd>ObsidianToday<cr>", desc = "Obsidian Today" },
		{ "<leader>os", "<cmd>ObsidianSearch<cr>", desc = "Search Obsidian notes" },
		{ "<leader>oq", "<cmd>ObsidianQuickSwitch<cr>", desc = "Switch note" },
	},
}
