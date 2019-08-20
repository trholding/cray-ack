for _, plat in ipairs(vars.plats) do
	acklibrary {
		name = "lib_"..plat,
		srcs = { "./*.s" }, -- dvi8.s
		vars = { plat = plat },
	}
end

