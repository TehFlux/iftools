/**
 * ==========================================================================
 * Copyright © 2011 Jörn P. Meier
 * All rights reserved.
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifobject.js          Ionflux Object Base System.
 * ==========================================================================
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 *  - Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the copyright holders nor the names of the 
 *    contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * ==========================================================================
 */

// Ionflux Object Base System namespace.
var IFObjectBase = {
    // Nothing here.
};

// Undefined check.
IFObjectBase.isUndefined = function(v)
{
    if (typeof(v) == 'undefined')
        return true;
    return false;
}

/**
 * Default argument support.
 *
 * v             -- Value.
 * defaultValue  -- Default value.
 *
 * Returns the default value if the argument is not defined.
 */
IFObjectBase.defaultArg = function(v, defaultValue)
{
    if (typeof(v) == 'undefined')
        return defaultValue;
    return v;
}

// Debug output.
IFObjectBase.debug = function(msg, source, debugItemClass, debugElementID)
{
    var s0 = IFObjectBase.defaultArg(source, null);
    var de0 = IFObjectBase.defaultArg(debugElementID, 'debug');
    var dc0 = IFObjectBase.defaultArg(debugItemClass, 'ibDebugItem');
    var d = $(de0);
    if (d == null)
        return;
    var e = new Element('div', { 'class' : dc0 });
    if (s0 != null)
        e.insert('[' + s0 + '] DEBUG: ' + msg);
    else
        e.insert('DEBUG: ' + msg);
    d.insert(e, { position: 'top' });
}

// Assertion.
IFObjectBase.assert = function(msg, source, assertion, assertItemClassOK, 
    assertItemClassFailed, assertElementID)
{
    var s0 = IFObjectBase.defaultArg(source, null);
    var ae0 = IFObjectBase.defaultArg(assertElementID, 'debug');
    var ac0 = IFObjectBase.defaultArg(assertItemClassOK, 'ibAssertItemOK');
    var ac1 = IFObjectBase.defaultArg(assertItemClassFailed, 'ibAssertItemFailed');
    if (assertion)
        IFObjectBase.debug(msg + ' (OK)', s0, ac0, ae0);
    else
        IFObjectBase.debug(msg + ' (FAILED)', s0, ac1, ae0);
}

/**
 * Get random character.
 * 
 * useChars  -- Characters to be used.
 * 
 * Get a random character from the specified range. If no range is specified, 
 * a random alphanumeric character or underscore will be returned.
 */
IFObjectBase.randomChar = function(useChars)
{
    var c0 = IFObjectBase.defaultArg(useChars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        + "abcdefghijklmnopqrstuvwxyz_0123456789");
    var i = Math.floor(Math.random() * c0.length);
    return c0.charAt(i);
}

/**
 * Get random string.
 * 
 * l         -- Length.
 * useChars  -- Characters to be used.
 * 
 * Get a random string of the specified length from the specified character 
 * range. If no range is specified, alphanumeric characters and the underscore 
 * will be used.
 */
IFObjectBase.randomString = function(l, useChars)
{
    var l0 = IFObjectBase.defaultArg(l, 20);
    var c0 = IFObjectBase.defaultArg(useChars, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        + "abcdefghijklmnopqrstuvwxyz_0123456789");
    var r = "";
    for (var i = 0; i < l; i++)
        r += IFObjectBase.randomChar(c0);
    return r;
}

/**
 * Convert string to byte array.
 *
 * s   -- String.
 *
 * Convert a string to a byte array.
 */
IFObjectBase.stringToBytes = function(s)
{
    var result = [];
    for (var i = 0; i < s.length; i++)
    {
        var c0 = s.charCodeAt(i);
        result.push(c0);
    }
    return result;
}

/**
 * Convert byte array to string.
 *
 * s   -- String.
 *
 * Convert a byte array to a string.
 */
IFObjectBase.bytesToString = function(b)
{
    var result = "";
    for (var i = 0; i < b.length; i++)
    {
        var c0 = String.fromCharCode(b[i]);
        result += c0;
    }
    return result;
}

/**
 * Get encoded data length.
 * 
 * Get the length the data will have when encoded in an IFObjectBase 
 * literal string.
 */
IFObjectBase.getEncodedLength = function(d)
{
    var b0 = IFObjectBase.stringToBytes(d);
    var l0 = 0;
    for (var i = 0; i < b0.length; i++)
    {
        var c0 = b0[i];
        if (c0 < 128)
            l0 += 1;
        else
        if (c0 < 2048)
            l0 += 2;
        else
        if (c0 < 65536)
            l0 += 3;
        else
        if (c0 < 2097152)
            l0 += 4;
        else
        if (c0 < 67108864)
            l0 += 5;
        else
        if (c0 < 2147483648)
            l0 += 6;
        else
            throw "[IFObjectBase.getEncodedLength] ERROR: "
                "Character not representable by UTF-8.";
    }
    return l0;
}

/** 
 * Unpack object.
 *
 * s    -- String.
 *
 * Unpack an object from an IFObjectBase literal string.
 */
IFObjectBase.unpackObject = function(s, target)
{
    var prefix = "%%";
    if (s.substr(0, prefix.length) != prefix)
        throw "[IFObjectBase.unpackObject] ERROR: Prefix expected.";
    var p0 = s.indexOf(":");
    if (p0 == -1)
        throw "[IFObjectBase.unpackObject] ERROR: Separator expected.";
    target.name = s.substr(prefix.length, p0 - prefix.length);
    var p1 = s.indexOf(":", p0 + 1);
    if (p0 == -1)
        throw "[IFObjectBase.unpackObject] ERROR: Separator expected.";
    target.encoding = s.substr(p0 + 1, p1 - p0 - 1);
    p0 = p1;
    p1 = s.indexOf(":", p0 + 1);
    if (p0 == -1)
        throw "[IFObjectBase.unpackObject] ERROR: Separator expected.";
    target.dataLength = parseInt(s.substr(p0 + 1, p1 - p0 - 1));
    p0 = p1;
    p1 = s.indexOf(":", p0 + 1);
    if (p0 == -1)
        throw "[IFObjectBase.unpackObject] ERROR: Separator expected.";
    target.data = s.substr(p0 + 1);
    var l0 = IFObjectBase.getEncodedLength(target.data);
    if (l0 != target.dataLength)
        throw "[IFObjectBase.unpackObject] ERROR: Data length mismatch "
            "(length = " + l0 + ", expected " + target.dataLength 
            + ").";
}

/**
 * Unpack unsigned integer.
 * 
 * s   -- String.
 *
 * Unpack an unsigned integer from an IFObjectBase literal string. Returns 
 * the resulting integer and the offset for the next data item.
 */
IFObjectBase.unpackUInt = function(s, offset)
{
    var p0 = IFObjectBase.defaultArg(offset, 0);
    var d0 = s.substr(p0, 4);
    var l0 = Number(jspack.Unpack("L", IFObjectBase.stringToBytes(d0)));
    p0 += 4;
    return [l0, p0];
}

/**
 * Unpack integer.
 * 
 * s   -- String.
 *
 * Unpack an integer from an IFObjectBase literal string. Returns the 
 * resulting integer and the offset for the next data item.
 */
IFObjectBase.unpackInt = function(s, offset)
{
    var p0 = IFObjectBase.defaultArg(offset, 0);
    var d0 = s.substr(p0, 4);
    var l0 = Number(jspack.Unpack("l", IFObjectBase.stringToBytes(d0)));
    p0 += 4;
    return [l0, p0];
}

/**
 * Unpack double.
 * 
 * s   -- String.
 *
 * Unpack a double from an IFObjectBase literal string. Returns the 
 * resulting double and the offset for the next data item.
 */
IFObjectBase.unpackDouble = function(s, offset)
{
    var p0 = IFObjectBase.defaultArg(offset, 0);
    var d0 = s.substr(p0, 8);
    var l0 = Number(jspack.Unpack("d", IFObjectBase.stringToBytes(d0)));
    p0 += 8;
    return [l0, p0];
}

/**
 * Unpack string.
 * 
 * s   -- String.
 *
 * Unpack a string from an IFObjectBase literal string. Returns the 
 * resulting string and the offset for the next data item.
 */
IFObjectBase.unpackString = function(s, offset)
{
    var p0 = IFObjectBase.defaultArg(offset, 0);
    var r0 = IFObjectBase.unpackUInt(s, offset)
    var l0 = r0[0];
    p0 = r0[1]
    var r0 = s.substr(p0, l0);
    p0 += l0;
    return [r0, p0];
}

/**
 * Pack unsigned integer.
 * 
 * v   -- Value.
 *
 * Pack an unsigned integer for use in a IFObjectBase literal string.
 */
IFObjectBase.packUInt = function(v)
{
    return IFObjectBase.bytesToString(jspack.Pack("L", [v]));
}

/**
 * Pack integer.
 * 
 * v   -- Value.
 *
 * Pack an integer for use in a IFObjectBase literal string.
 */
IFObjectBase.packInt = function(v)
{
    return IFObjectBase.bytesToString(jspack.Pack("l", [v]));
}

/**
 * Pack double.
 * 
 * v   -- Value.
 *
 * Pack a double for use in a IFObjectBase literal string.
 */
IFObjectBase.packDouble = function(v)
{
    return IFObjectBase.bytesToString(jspack.Pack("d", [v]));
}

/**
 * Pack string.
 * 
 * v   -- Value.
 *
 * Pack a string for use in a IFObjectBase literal string.
 */
IFObjectBase.packString = function(v)
{
    return IFObjectBase.bytesToString(jspack.Pack("L", [v.length])) + v;
}

/** 
 * Pack object.
 *
 * v    -- Object.
 *
 * Pack an object for use in a IFObjectBase literal string.
 */
IFObjectBase.packObject = function(v)
{
    var prefix = "%%";
    var l0 = IFObjectBase.getEncodedLength(v.data);
    var result = prefix + v.name + ":utf8:" + l0 + ":" + v.data;
    return result;
}

/// IFObject proxy class.
IFObjectBase.IFObject = Class.create({
    
    initialize: function()
    {
        this.name = "IFObject";
        this.id = "";
        this.idNum = 0;
        this.data = "";
    },
    
    pack: function()
    {
        return IFObjectBase.packObject(this);
    },
    
    unpack: function(s)
    {
        var d0 = IFObjectBase.unpackObject(s);
        /* NOTE: Setting the name without a check is acceptable, since we 
                 have no information about base classes and derived classes 
                 may want to call this function in their unpack() 
                 implementation. */
        this.name = d0.name;
        this.id = d0.id;
        this.idNum = d0.idNum;
        this.data = d0.data;
    }
    
});

