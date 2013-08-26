{section createStructDecl}{foreach st in struct}
 
/** {$st.desc}.{if (class.group.shortDesc == "") && (class.group.name != "")}
 * \\ingroup {$class.group.name}{/if}
 */
struct {if class.linkagePrefix != ""}{$class.linkagePrefix} {else}{if project.linkagePrefix != ""}{$project.linkagePrefix} {/if}{/if}{$st.name}
\{{foreach fi in st.field}
	/// {$fi.desc}.
	{$fi.type} {$fi.name};{/foreach}{foreach cn in st.constant}
	/// {$cn.desc}.
	static const {$cn.type} {$cn.name};{/foreach}{if st.refCount.enabled == "true"}
	/// Reference counting information.
	Ionflux::ObjectBase::IFObjectRefInfo* refInfo;{/if}
\};{/foreach}{/section}
