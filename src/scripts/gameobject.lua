local GameObject = {}

local methods = {
    destroy = function(object)
        setmetatable(object, {})
    end
}

local meta = {
    __index = function(object, index)
        local public, private = rawget(object, "public"), rawget(object, "private")
        local value = nil
        
        if public[index] then
            value = public[index]
        elseif methods[index] then
            value = methods[index] 
        else
            value = private.children[index]
        end
        return value
    end,
    __newindex = function(object, index, value)
        local public, private = rawget(object, "public"), rawget(object, "private")
        
        if public[index] then
            public[index] = value
        end
    end,
    __gc = function(object)
        print("Destroying " .. object.name)
    end
}

GameObject.create = function(name)
    return setmetatable({
        public = {
            name = name;
            parent = nil;
        };
        private = {
            children = {};
        }
    }, meta)
end

return GameObject