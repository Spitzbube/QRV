#
# System call template file. Gets sourced by mkkercalls.sh
#

function syscall_file_hdr
{
    echo
    echo ".intel_syntax noprefix"
    echo
}

function gen_call {
    typeset name="$1"
    typeset kcnum="$2"
    typeset nparms="$3"
    typeset rent="$4"
    typeset neglist="$5"

    echo
    echo "	.align 4"
    echo "	.global ${name}"
    echo
    echo "${name}:"
    echo "#if defined(VARIANT_p)"
    echo "	push	ebp"
    echo "	mov	ebp, esp"
    echo
    echo "	.data"
    echo "	.align 4"
    echo ".LP1:"
    echo "	.long 0"
    echo
    echo "	.text"
    echo "	mov	edx, offset .LP1"
    echo "	call	_mcount"
    echo "	pop	ebp"
    echo "#endif"

    for neg in $neglist; do
        let "off = $neg * 4"
        echo "	neg	dword ptr [esp+$off]"
    done

    echo "	mov	eax, ${kcnum}"
    echo "#if defined(__PIC__)"
    echo "	call	.L1_$name"
    echo ".L1_$name:"
    echo "	pop	edx"
    echo "	mov	ecx, edx"
    echo "	add	ecx, _GLOBAL_OFFSET_TABLE_ + (.-.L1_$name)"
    echo "	add	edx, .L2_$name - .L1_$name"
    echo "	test	dword ptr [ecx+__cpu_flags@GOTOFF], X86_CPU_SEP"
    echo "#else"
    echo "	test	dword ptr [__cpu_flags], X86_CPU_SEP"
    echo "	mov	edx, .L2_$name"
    echo "#endif"
    echo "	jz	1f"
    echo "	mov	ecx, esp"
    echo "	sysenter"
    echo ".L2_$name:"
    echo "	ret"
    echo "2:"

    case ${rent} in
    NONE)
        echo "	.extern __ker_err"
        echo "#if defined(__PIC__)"
        echo "	add	edx, _GLOBAL_OFFSET_TABLE_+ (.-.L2)"
        echo "	mov	edx, [edx+__ker_err]"
        echo "	jmp	edx"
        echo "#else"
        echo "	jmp	__ker_err"
        echo "#endif"
        ;;

    NORMAL)
        echo "	ret"
        ;;

    NEGATIVE)
        echo "	neg	eax"
        echo "	ret"
        ;;
    esac

    echo "1:"
    echo "	int	0x28"
    echo "	ret"

    case ${rent} in
    NONE)
        echo "#if defined(__PIC__)"
        echo "	jmp	2b"
        echo "#else"
        echo "	jmp	__ker_err"
        echo "#endif"
        ;;

    NORMAL)
        echo "	ret"
        ;;

    NEGATIVE)
        echo "	neg	eax"
        echo "	ret"
	;;
    esac

    echo "	.type ${name}, @function"
    echo "	.size ${name}, .-${name}"
    echo "//-------------------------------------------------------------------------------"
}
