import unreal

DS = unreal.DemoStruct(0)
DBFI = unreal.DemoBlueprintFunctionLibrary

print("locked: %s" % DBFI.is_struct_locked(DS))

unreal.DemoBlueprintFunctionLibrary.lock_struct(DS)
print("locked: %s" % DBFI.is_struct_locked(DS))
unreal.DemoBlueprintFunctionLibrary.unlock_struct(DS)
print("locked: %s" % DBFI.is_struct_locked(DS))