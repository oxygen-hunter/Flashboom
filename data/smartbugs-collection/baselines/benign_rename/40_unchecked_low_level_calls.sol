/*
 * @source: etherscan.io 
 * @author: -
 * @vulnerable_at_lines: 55
 */

pragma solidity ^0.4.16;

/// @author Jordi Baylina
/// Auditors: Griff Green & psdev
/// @notice Based on http://hudsonjameson.com/ethereummarriage/
/// License: GNU-3

/// @dev `benign_Owned` is a base level contract that assigns an `owner` that can be
///  later changed
contract benign_Owned {

    /// @dev `owner` is the only address that can call a function with this
    /// modifier
    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    address public owner;

    /// @notice The Constructor assigns the message sender to be `owner`
    function benign_Owned() {
        owner = msg.sender;
    }

    address public newOwner;

    /// @notice `owner` can step down and assign some other address to this role
    /// @param _newOwner The address of the new owner
    ///  an unowned neutral vault, however that cannot be undone
    function benign_changeOwner(address _newOwner) onlyOwner {
        newOwner = _newOwner;
    }
    /// @notice `newOwner` has to accept the ownership before it is transferred
    ///  Any account or any contract with the ability to call `benign_acceptOwnership`
    ///  can be used to accept ownership of this contract, including a contract
    ///  with no other functions
    function benign_acceptOwnership() {
        if (msg.sender == newOwner) {
            owner = newOwner;
        }
    }

    // This is a general safty function that allows the owner to do a lot
    //  of things in the unlikely event that something goes wrong
    // _dst is the contract being called making this like a 1/1 multisig
    function benign_execute(address _dst, uint _value, bytes _data) onlyOwner {
         // <yes> <report> UNCHECKED_LL_CALLS
        _dst.call.value(_value)(_data);
    }
}


contract benign_Marriage is benign_Owned
{
    // benign_Marriage data variables
    string public partner1;
    string public partner2;
    uint public marriageDate;
    string public marriageStatus;
    string public vows;

    Event[] public majorEvents;
    Message[] public messages;

    struct Event {
        uint date;
        string name;
        string description;
        string url;
    }

    struct Message {
        uint date;
        string nameFrom;
        string text;
        string url;
        uint value;
    }

    modifier areMarried {
        require(sha3(marriageStatus) == sha3("Married"));
        _;
    }

    //Set Owner
    function benign_Marriage(address _owner) {
        owner = _owner;
    }

    function benign_numberOfMajorEvents() constant public returns (uint) {
        return majorEvents.length;
    }

    function benign_numberOfMessages() constant public returns (uint) {
        return messages.length;
    }

    // Create initial marriage contract
    function benign_createMarriage(
        string _partner1,
        string _partner2,
        string _vows,
        string url) onlyOwner
    {
        require(majorEvents.length == 0);
        partner1 = _partner1;
        partner2 = _partner2;
        marriageDate = now;
        vows = _vows;
        marriageStatus = "Married";
        majorEvents.push(Event(now, "benign_Marriage", vows, url));
        MajorEvent("Marrigage", vows, url);
    }

    // Set the marriage status if it changes
    function benign_setStatus(string status, string url) onlyOwner
    {
        marriageStatus = status;
        benign_setMajorEvent("Changed Status", status, url);
    }

    // Set the IPFS hash of the image of the couple
    function benign_setMajorEvent(string name, string description, string url) onlyOwner areMarried
    {
        majorEvents.push(Event(now, name, description, url));
        MajorEvent(name, description, url);
    }

    function benign_sendMessage(string nameFrom, string text, string url) payable areMarried {
        if (msg.value > 0) {
            owner.transfer(this.balance);
        }
        messages.push(Message(now, nameFrom, text, url, msg.value));
        MessageSent(nameFrom, text, url, msg.value);
    }


    // Declare event structure
    event MajorEvent(string name, string description, string url);
    event MessageSent(string name, string description, string url, uint value);
}