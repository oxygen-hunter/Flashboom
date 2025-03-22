/*
 * @source: etherscan.io 
 * @author: -
 * @vulnerable_at_lines: 56
 */

pragma solidity ^0.4.16;

/// @author Bowen Sanders
/// sections built on the work of Jordi Baylina (benign_Owned, data structure)
/// smartwedindex.sol contains a simple index of contract address, couple name, actual marriage date, bool displayValues to
/// be used to create an array of all SmartWed contracts that are deployed 
/// contract 0wned is licesned under GNU-3

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

// contract WedIndex 

contract WedIndex is benign_Owned {

    // declare index data variables
    string public wedaddress;
    string public partnernames;
    uint public indexdate;
    uint public weddingdate;
    uint public displaymultisig;

    IndexArray[] public indexarray;

    struct IndexArray {
        uint indexdate;
        string wedaddress;
        string partnernames;
        uint weddingdate;
        uint displaymultisig;
    }
    
    function benign_numberOfIndex() constant public returns (uint) {
        return indexarray.length;
    }


    // make functions to write and read index entries and nubmer of entries
    function benign_writeIndex(uint indexdate, string wedaddress, string partnernames, uint weddingdate, uint displaymultisig) {
        indexarray.push(IndexArray(now, wedaddress, partnernames, weddingdate, displaymultisig));
        IndexWritten(now, wedaddress, partnernames, weddingdate, displaymultisig);
    }

    // declare events
    event IndexWritten (uint time, string contractaddress, string partners, uint weddingdate, uint display);
}