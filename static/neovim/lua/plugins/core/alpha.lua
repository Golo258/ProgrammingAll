return {
	"goolord/alpha-nvim",
	dependencies = { "nvim-tree/nvim-web-devicons" },
	config = function()
		local alpha = require("alpha")
		local dashboard = require("alpha.themes.dashboard")

		-- Custom header with GoloVim
		dashboard.section.header.val = {
			[[   ¦¦¦¦¦¦+   ¦¦¦¦¦¦+ ¦¦+      ¦¦¦¦¦¦+ ¦¦+   ¦¦+¦¦+¦¦¦+   ¦¦¦+ ]],
			[[  ¦¦+----+  ¦¦+---¦¦+¦¦¦     ¦¦+---¦¦+¦¦¦   ¦¦¦¦¦¦¦¦¦¦+ ¦¦¦¦¦ ]],
			[[  ¦¦¦  ¦¦¦+ ¦¦¦   ¦¦¦¦¦¦     ¦¦¦   ¦¦¦¦¦¦   ¦¦¦¦¦¦¦¦+¦¦¦¦+¦¦¦ ]],
			[[  ¦¦¦   ¦¦¦ ¦¦¦   ¦¦¦¦¦¦     ¦¦¦   ¦¦¦¦¦¦   ¦¦¦¦¦¦¦¦¦+¦¦++¦¦¦ ]],
			[[  +¦¦¦¦¦¦++ +¦¦¦¦¦¦++¦¦¦¦¦¦¦++¦¦¦¦¦¦+++¦¦¦¦¦¦++¦¦¦¦¦¦ +-+ ¦¦¦ ]],
			[[   +-----+   +-----+ +------+ +-----+  +-----+ +-++-+     +-+ ]],
			[[                                                              ]],
			[[                 Welcome to your GoloVim.                     ]],
			[[                 What are we coding today                     ]],
		}

		-- Custom menu buttons
		dashboard.section.buttons.val = {
			dashboard.button("e", "Create  > New file", ":ene <BAR> startinsert <CR>"),
			dashboard.button("f", "Find  > Find file", ":Telescope find_files<CR>"),
			dashboard.button("r", "Recent  > Recent", ":Telescope oldfiles<CR>"),
			dashboard.button("s", "Settings  > Settings", ":e $MYVIMRC | :cd %:p:h | split . | wincmd k | pwd<CR>"),
			dashboard.button("q", "Quit  > Quit NVIM", ":qa<CR>"),
		}

		-- Send config to alpha
		alpha.setup(dashboard.opts)

		-- Disable folding in dashboard
		vim.cmd([[autocmd FileType alpha setlocal nofoldenable]])
	end,
}
