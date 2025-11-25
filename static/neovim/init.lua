local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not (vim.uv or vim.loop).fs_stat(lazypath) then
	local lazyrepo = "https://github.com/folke/lazy.nvim.git"
	local out = vim.fn.system({ "git", "clone", "--filter=blob:none", "--branch=stable", lazyrepo, lazypath })
	if vim.v.shell_error ~= 0 then
		vim.api.nvim_echo({
			{ "Failed to clone lazy.nvim:\n", "ErrorMsg" },
			{ out, "WarningMsg" },
			{ "\nPress any key to exit..." },
		}, true, {})
		vim.fn.getchar()
		os.exit(1)
	end
end
vim.opt.rtp:prepend(lazypath)

local opts = {}
vim.g.mapleader = " "
vim.g.maplocalleader = " "
-- Map all plugins
require("lazy").setup({
	{ import = "plugins.core" },
	{ import = "plugins.lsp" },
	{ import = "plugins.ui" },
	{ import = "plugins.coding" },
	{ import = "plugins.themes" },
	{ import = "plugins.notes" },
	-- FIX: fix someday  the replace function
 	-- { dir = vim.fn.stdpath("config") .. "/lua/local/easy-replace" },
})
require("vim-mapping")

-- settings to make neo-tree not blocke after :wq
vim.api.nvim_create_autocmd("QuitPre", {
	callback = function()
		-- Zamknij Neo-tree zanim wyjdzie z Neovim
		require("neo-tree.command").execute({ action = "close" })
	end,
})

-- setting for grovvy
vim.filetype.add({
	extension = {
		groovy = "groovy",
	},
})

-- Setup for git fugitive
vim.api.nvim_create_autocmd("BufWinEnter", {
	pattern = { "gitcommit", "fugitiveblame" },
	callback = function()
		vim.cmd("wincmd H")
	end,
})

-- settings for terminal xterm
vim.opt.termguicolors = true

-- auo save previous session
vim.api.nvim_create_autocmd("VimEnter", {
	callback = function()
		if vim.fn.argc() == 0 then
			require("persistence").load()
		end
	end,
})

-- setup for occurrences  taken word
vim.keymap.set("v", "<leader>er", function()
	local input = vim.fn.input("Replace with: ")
	if input == "" then
		return
	end

	-- get fresh mark positions
	local start_pos = vim.api.nvim_buf_get_mark(0, "<")
	local end_pos = vim.api.nvim_buf_get_mark(0, ">")
	local line = vim.fn.getline(start_pos[1])
	local col_start = start_pos[2] + 1
	local col_end = end_pos[2] + 1
	local replaced = line:sub(1, col_start - 1) .. input .. line:sub(col_end)
	vim.fn.setline(start_pos[1], replaced)
end, { desc = "Replace selection", noremap = true, silent = true })

-- setup for replacing every occurrences of word
-- TODO:fix  it someday
vim.keymap.set("v", "<leader>eR", function()
  local start_pos = vim.fn.getpos("'<")
  local end_pos = vim.fn.getpos("'>")
  local line = vim.fn.getline(start_pos[2])
  local col_start = start_pos[3]
  local col_end = end_pos[3]
  local target = line:sub(col_start, col_end - 1)

  -- Debug print
  print("TARGET TO REPLACE: [" .. target .. "]")

  if target == "" then
    vim.notify("No text selected", vim.log.levels.WARN)
    return
  end

  local input = vim.fn.input("Replace all '" .. target .. "' with: ")
  if input == "" then return end

  local lines_to_replace = {}
  for lnum = 1, vim.fn.line("$") do
    local current = vim.fn.getline(lnum)
    local replaced = current:gsub(vim.pesc(target), input)
    if replaced ~= current then
      table.insert(lines_to_replace, { lnum = lnum, text = replaced })
    end
  end

  for _, item in ipairs(lines_to_replace) do
    vim.fn.setline(item.lnum, item.text)
  end
end, { desc = "Replace all occurrences (safe)", noremap = true, silent = true })

