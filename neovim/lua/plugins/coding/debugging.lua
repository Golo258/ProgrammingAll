return {
	"mfussenegger/nvim-dap",
	dependencies = {
		"rcarriga/nvim-dap-ui",
		"nvim-neotest/nvim-nio",
	},
	config = function()
		local dap, dapui = require("dap"), require("dapui")

		-- resize Neo-tree po debugowaniu
		local function resize_neo_tree(width)
			for _, win in ipairs(vim.api.nvim_list_wins()) do
				local bufname = vim.api.nvim_buf_get_name(vim.api.nvim_win_get_buf(win))
				if bufname:match("neo%-tree") then
					vim.api.nvim_win_set_width(win, width)
				end
			end
		end

		-- minimalistyczny layout debug panelu
		dapui.setup({
			layouts = {
				{
					elements = {
						{ id = "scopes", size = 0.75 },
						{ id = "breakpoints", size = 0.25 },
					},
					size = 40,
					position = "left",
				},
			},
			controls = { enabled = false },
		})

		-- po starcie debugowania
		dap.listeners.after.event_initialized["dapui_config"] = function()
			-- zamknij neo-tree
			pcall(function()
				require("neo-tree.command").execute({ action = "close" })
			end)

			-- otwórz UI i terminal
			dapui.open()
			require("dap").repl.open(nil, "belowright split")
			vim.cmd("resize 15")
		end

		-- po zakonczeniu debugowania
		local function close_debug()
			dapui.close()
			resize_neo_tree(35)
		end

		dap.listeners.before.event_terminated["dapui_config"] = close_debug
		dap.listeners.before.event_exited["dapui_config"] = close_debug

		-- konfiguracja debugpy dla pythona
		dap.adapters.python = {
			type = "executable",
			command = "python",
			args = { "-m", "debugpy.adapter" },
		}

		dap.configurations.python = {
			{
				type = "python",
				request = "launch",
				name = "Launch file",
				program = "${file}",
				console = "integratedTerminal",
				justMyCode = false,
				outputCapture = "std",
				pythonPath = function()
					return "python"
				end,
			},
		}

		-- MAPKI
		vim.keymap.set("n", "<F4>", dap.toggle_breakpoint, { desc = "Toggle breakpoint" })
		vim.keymap.set("n", "<F5>", dap.continue, { desc = "Start/Continue debug" })
		vim.keymap.set("n", "<F9>", dap.step_over, { desc = "Step over" })
		vim.keymap.set("n", "<F10>", dap.step_into, { desc = "Step into" })
		vim.keymap.set("n", "<F6>", function()
			dap.terminate()
			close_debug()
		end, { desc = "Stop debug and cleanup" })
	end,
}
