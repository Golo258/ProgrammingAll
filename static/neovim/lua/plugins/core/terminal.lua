return {
	"akinsho/toggleterm.nvim",
	version = "*",
	config = function()
		require("toggleterm").setup({
			direction = "float", -- ?? domyslnie float
			open_mapping = [[<leader>tt]],
			start_in_insert = true,
			insert_mappings = true,
			persist_size = true,
			shell = vim.o.shell,

			-- ?? Matrix Float Styl
			float_opts = {
				border = "rounded",
				winblend = 0,
				highlights = {
					border = "FloatBorder",
					background = "NormalFloat",
				},
			},
		})

		local Terminal = require("toggleterm.terminal").Terminal

		-- Terminal z Elixirem (iex -S mix)
		local elixir = Terminal:new({ cmd = "iex -S mix", hidden = true, direction = "float" })
		vim.keymap.set("n", "<leader>te", function()
			elixir:toggle()
		end, { desc = "Elixir IEx -S Mix" })

		-- Terminal z bashowym REPL (np. robot.sh, gears)
		local bash = Terminal:new({ cmd = "bash", hidden = true, direction = "float" })
		vim.keymap.set("n", "<leader>tb", function()
			bash:toggle()
		end, { desc = "Bash Terminal" })

		-- ?? Alternatywa do domyslnego terminala (float + matrix)
		vim.keymap.set("n", "<leader>tq", "<cmd>ToggleTerm<CR>", { desc = "Toggle default terminal" })
	end,
}
