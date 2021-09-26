print("Success = ", pcall(function()
    local Success, GameObject = pcall(require, "src/scripts/gameobject")
        
    local p = GameObject.create("pie")
    
    print(p)
    
    p:destroy()
    
    print(p)

    --fix this yes?
end))