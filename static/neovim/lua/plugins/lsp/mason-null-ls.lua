return {
	{
		"jay-babu/mason-null-ls.nvim",
		dependencies = { "williamboman/mason.nvim", "nvimtools/none-ls.nvim" },
		config = function()
			require("mason-null-ls").setup({
				ensure_installed = {
					"stylua",
					"prettier",
					"mix",
					"black",
					"isort",
					"google_java_format",
				},
				automatic_installation = true,
			})
		end,
	},
}
