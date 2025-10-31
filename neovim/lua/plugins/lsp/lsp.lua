return {
	{
		"neovim/nvim-lspconfig",
		lazy = false,
		priority = 1000,
		config = function()
			local lspconfig = require("lspconfig")
			local capabilities = require("cmp_nvim_lsp").default_capabilities()

			lspconfig.lua_ls.setup({
				capabilities = capabilities,
				settings = {
					Lua = {
						diagnostics = {
							globals = { "vim" },
						},
					},
				},
			})

			lspconfig.elixirls.setup({
				capabilities = capabilities,
				cmd = { vim.fn.stdpath("data") .. "/mason/bin/elixir-ls" },
				settings = {
					elixirLS = {
						dialyzerEnabled = false,
						fetchDeps = false,
					},
				},
			})

			lspconfig.pyright.setup({
				capabilities = capabilities,
			})

			lspconfig.groovyls.setup({
				capabilities = capabilities,
			})

			vim.keymap.set("n", "H", vim.lsp.buf.hover, {})
			vim.keymap.set("n", "gd", vim.lsp.buf.definition, {})
			vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action, {})
		end,
	},
	{
		"williamboman/mason-lspconfig.nvim",
		dependencies = { "neovim/nvim-lspconfig" },
		config = function()
			require("mason-lspconfig").setup({
				ensure_installed = {
					"lua_ls",
					"elixirls",
					"pyright",
					"groovyls",
				},
			})
		end,
	},
}
