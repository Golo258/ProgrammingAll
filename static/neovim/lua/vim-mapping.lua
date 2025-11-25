-- mapping for moving into terminals
vim.keymap.set('n', '<c-left>',  '<c-w>h')
vim.keymap.set('n', '<c-down>',  '<c-w>j')
vim.keymap.set('n', '<c-up>',    '<c-w>k')
vim.keymap.set('n', '<c-right>', '<c-w>l')
-- mapping other options
vim.cmd("set expandtab") 
vim.cmd("set tabstop=2")
vim.cmd("set softtabstop=2")
vim.cmd("set shiftwidth=2")

-- Line with number setup
vim.opt.number = true
vim.opt.relativenumber = false
