return {
	"nvim-treesitter/nvim-treesitter",
	build = ":TSUpdate",
	config = function()
		local treesitterconfig = require("nvim-treesitter.configs")
		treesitterconfig.setup({
      auto_install = true,
			highlight = { enable = true },
			indent = { enable = true },
		})
	end,
}
