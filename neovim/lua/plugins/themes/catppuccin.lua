return {
	{
		"catppuccin/nvim",
		name = "catppuccin",
		lazy = false,
		priority = 1000,
		config = function()
			print("catppuccin sie laduje!")

			require("catppuccin").setup({
				integrations = {
					neotree = true,
					dap = true,
					cmp = true,
					treesitter = true,
					native_lsp = {
						enabled = true,
					},
				},
				custom_highlights = function(colors)
					return {
						FloatBorder = { fg = "#00ff5f", bg = "#0f0f0f" },
						NormalFloat = { bg = "#0f0f0f" },
					}
				end,
			})

			vim.cmd.colorscheme("catppuccin")

			-- ?? Ustawienia floatów po colorscheme (autocmd i recznie)
			vim.api.nvim_create_autocmd("ColorScheme", {
				pattern = "*",
				callback = function()
					vim.api.nvim_set_hl(0, "FloatBorder", {}) -- zrywa linka
					vim.api.nvim_set_hl(0, "FloatBorder", { fg = "#00ff5f", bg = "#0f0f0f" })
					vim.api.nvim_set_hl(0, "NormalFloat", { bg = "#0f0f0f" })
				end,
			})

			-- ?? I od razu ustaw na twardo:
			vim.api.nvim_set_hl(0, "FloatBorder", {})
			vim.api.nvim_set_hl(0, "FloatBorder", { fg = "#00ff5f", bg = "#0f0f0f" })
			vim.api.nvim_set_hl(0, "NormalFloat", { bg = "#0f0f0f" })
		end,
	},
}
