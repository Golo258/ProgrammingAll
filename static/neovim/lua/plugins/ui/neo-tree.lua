return {
	"nvim-neo-tree/neo-tree.nvim",
	branch = "v3.x",
	dependencies = {
		"nvim-lua/plenary.nvim",
		"nvim-tree/nvim-web-devicons",
		"MunifTanjim/nui.nvim",
	},
	config = function()
		vim.keymap.set("n", "<c-n>", ":Neotree filesystem reveal left<cr>")
		vim.keymap.set("n", "<c-b>", ":Neotree close<cr>", {})

		local function split_and_open(direction, node)
			local current_win = vim.api.nvim_get_current_win()
			vim.cmd("wincmd p")

			if direction == "left" then
				vim.cmd("leftabove vsplit")
			elseif direction == "right" then
				vim.cmd("rightbelow vsplit")
			elseif direction == "up" then
				vim.cmd("aboveleft split")
			elseif direction == "down" then
				vim.cmd("belowright split")
			end

			vim.cmd("edit " .. node.path)
			vim.api.nvim_set_current_win(current_win)
		end

		-- setup for neo-tree icons
		require("nvim-web-devicons").setup({
			override = {
				robot = {
					icon = "??",
					color = "#cc241d",
					name = "Robot",
				},
				groovy = {
					icon = "?",
					color = "#4298b8",
					name = "Groovy",
				},
				ex = {
					icon = "?",
					color = "#a074c4",
					name = "Elixir",
				},
				exs = {
					icon = "?",
					color = "#a074c4",
					name = "ElixirScript",
				},
			},
			default = true,
		})

		-- setup for mapping keyws
		require("neo-tree").setup({
			window = {
				position = "left",
				mappings = {
					["<C-l>"] = function(state)
						local node = state.tree:get_node()
						split_and_open("left", node)
					end,
					["<C-r>"] = function(state)
						local node = state.tree:get_node()
						split_and_open("right", node)
					end,
					["<C-u>"] = function(state)
						local node = state.tree:get_node()
						split_and_open("up", node)
					end,
					["<C-d>"] = function(state)
						local node = state.tree:get_node()
						split_and_open("down", node)
					end,
				},
			},
			filesystem = {
				window = {
					mappings = {
						["<C-x>"] = "expand_all_nodes",
					},
				},
			},
		})

		-- setup to auto open neo-tree after loading nvim file
		vim.api.nvim_create_autocmd("VimEnter", {
			callback = function()
				require("neo-tree.command").execute({ action = "show" })
			end,
		})
	end,
}
