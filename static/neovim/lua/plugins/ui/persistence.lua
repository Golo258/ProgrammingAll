--local persistence = require("persistence")
return {
	"folke/persistence.nvim",
	opts = {
		options = { "buffers", "curdir", "tabpages", "winsize" },
	},
	keys = {
		{
			"<leader>rs",
			function()
				require("persistence").load()
				vim.defer_fn(function()
					vim.cmd("Neotree show")
				end, 100)
			end,
			desc = "Respeore Session",
		},
		{
			"<leader>rls",
			function()
				require("persistence").load({ last = true })
				vim.defer_fn(function()
					vim.cmd("Neotree show")
				end, 100)
			end,
			desc = "Restore Last Session",
		},
		{
			"<leader>rns",
			function()
				require("persistence").stop()
			end,
			desc = "Don't Save Session",
		},
	},
}
