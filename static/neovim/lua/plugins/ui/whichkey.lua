return {
	{
		"folke/which-key.nvim",
		lazy = false,
		priority = 1000,
		config = function()
			require("which-key").setup({
				window = {
					border = "rounded",
					position = "bottom",
					padding = { 1, 2, 1, 2 },
					margin = { 0, 0, 0, 0 },
					winblend = 0,
				},
				layout = {
					spacing = 6,
					align = "center",
				},
				icons = {
					breadcrumb = "»",
					separator = "?",
					group = "+",
				},
			})
		end,
	},
}
