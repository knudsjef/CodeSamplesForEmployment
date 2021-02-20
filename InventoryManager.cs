using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Linq;
using System;


/** 
 * This class handles the inventory management for a game I am currently developing with some friends.
 * It is currently still in development, so there are some missing methods and less than satisfactory algorithms.
 */
public class InventoryManager : MonoBehaviour
{ 
    public enum PickupableTypes
    {
        Tool,
        Weapon,
        Drop,
        Herb,
        Misc,
        All
    }
    public static InventoryManager Instance { get; private set; }
    public bool IsActive 
    {
        get
        {
            return inventoryMenu.activeInHierarchy;
        }
    }
    private Pickupable[] hotBarItems = new Pickupable[10];
    private int currentlySelectedIndex = 0;
    private Vector2Int nextOpenSlot = Vector2Int.zero;

    [SerializeField]
    private GameObject selector;
    [SerializeField]
    private GameObject inventoryMenu, grid;
    [SerializeField]
    private Image itemCloseupImage;
    [SerializeField]
    private Text nameText;
    [SerializeField]
    private Text flavorText;
    private bool inventoryIsFull = false;
    private PauseManager pauseManagerInstance;

    public event EventHandler<InventoryHideShowEventArgs> InventoryHideShowEvent;
    public event EventHandler HidingInventoryMenu;

    public Pickupable CurrentlySelectedPickupable
    {
        get
        {
            return hotBarItems[currentlySelectedIndex];
        }
    }

    private IEnumerator Start()
    {
        Instance = this;
        yield return new WaitUntil(() => PauseManager.Instance != null);
        pauseManagerInstance = PauseManager.Instance;
        calculateNextOpenSlot();
    }

    #region <----Show Events---->
    /// <summary>
    /// Shows everything in the inventory
    /// </summary>
    public void ShowAll()
    {
        InventoryHideShowEvent.Invoke(this, new InventoryHideShowEventArgs(PickupableTypes.All));
    }

    /// <summary>
    /// Shows only weapons in inventory
    /// </summary>
    public void ShowWeapons()
    {
        InventoryHideShowEvent?.Invoke(this, new InventoryHideShowEventArgs(PickupableTypes.Weapon));
    }

    /// <summary>
    /// Shows only the miscellaneous items in inventory
    /// </summary>
    public void ShowMisc()
    {
        InventoryHideShowEvent?.Invoke(this, new InventoryHideShowEventArgs(PickupableTypes.Misc));
    }

    /// <summary>
    /// Shows only the herbs in the inventory
    /// </summary>
    public void ShowHerbs()
    {
        InventoryHideShowEvent?.Invoke(this, new InventoryHideShowEventArgs(PickupableTypes.Herb));
    }

    /// <summary>
    /// Shows only the drops in the inventory
    /// </summary>
    public void ShowDrops()
    {
        InventoryHideShowEvent?.Invoke(this, new InventoryHideShowEventArgs(PickupableTypes.Drop));
    }

    /// <summary>
    /// Shows only the tools in the inventory
    /// </summary>
    public void ShowTools()
    {
        InventoryHideShowEvent?.Invoke(this, new InventoryHideShowEventArgs(PickupableTypes.Tool));
    }
    #endregion

    /// <summary>
    /// Moves the selector sprite to a certain position in the inventory bar
    /// </summary>
    /// <param name="position">The position to move the selector to (0 based)</param>
    public void MoveSelector(int position)
    {
        currentlySelectedIndex = position;
        selector.transform.localPosition = new Vector2(50 * position - 225, selector.transform.localPosition.y);
    }

    /// <summary>
    /// Moves the selector sprite one position to the left, wrapping if necessary
    /// </summary>
    public void SelectLeft()
    {
        currentlySelectedIndex--;
        if (currentlySelectedIndex < 0)
        {
            currentlySelectedIndex = 9;
        }
        MoveSelector(currentlySelectedIndex);
    }

    /// <summary>
    /// Moves the selector sprite one position to the right, wrapping if necessary
    /// </summary>
    public void SelectRight()
    {
        currentlySelectedIndex++;
        if (currentlySelectedIndex > 9)
        {
            currentlySelectedIndex = 0;
        }
        MoveSelector(currentlySelectedIndex);
    }

    /// <summary>
    /// Toggles visibility of the inventory menu
    /// </summary>
    public void ShowHideInventoryMenu()
    {
        if (!inventoryMenu.activeInHierarchy)
        {
            pauseManagerInstance.GameIsPaused = true;
            inventoryMenu.SetActive(true);
            ShowAll();
        }
        else
        {
            HidingInventoryMenu.Invoke(this, null);
            pauseManagerInstance.GameIsPaused = false;
            inventoryMenu.SetActive(false);
        }
    }

    /// <summary>
    /// Force hides the inventory menu
    /// </summary>
    public void CloseInventoryMenu()
    {
        HidingInventoryMenu.Invoke(this, null);
        inventoryMenu.SetActive(false);
        pauseManagerInstance.GameIsPaused = false;
    }

    /// <summary>
    /// Adds item to the inventory
    /// </summary>
    /// <param name="item">The item to be added to the inventory</param>
    public void AddToInventory(Pickupable item)
    {
        calculateNextOpenSlot();
        if (inventoryIsFull)
        {
            //TODO: determine how to handle full inventory (add dialogue, overencumber user, etc.)
        }
        grid.transform.Find($"Row {nextOpenSlot.y}").Find($"{nextOpenSlot.x}").GetComponent<InventorySlot>().SetItemInSlot(item);
    }

    /// <summary>
    /// Calculates the next open slot in the inventory, including previous slots in case player moves items
    /// </summary>
    private void calculateNextOpenSlot()
    {
        //TODO: optimize this because O(n^2) is not good
        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 13; x++)
            {
                if (grid.transform.Find($"Row {y}").Find($"{x}").GetComponent<InventorySlot>().IsOpen)
                {
                    inventoryIsFull = false;
                    nextOpenSlot = new Vector2Int(x, y);
                    return;
                }
            }
        }
        inventoryIsFull = true;
    }

    /// <summary>
    /// Shows the info available on the selected item
    /// </summary>
    /// <param name="item">The selected item to show info on</param>
    public void ShowInfo(Pickupable item)
    {
        if (item != null)
        {
            itemCloseupImage.sprite = item.InventoryImage;
            nameText.text = item.Name;
            flavorText.text = item.Description;
        }
    }

    /// <summary>
    /// Transfers the item from the inventory to the hot bar
    /// </summary>
    /// <param name="item">The item to be transferred</param>
    /// <param name="slot">The hot bar index to add it to</param>
    public void AddItemToHotBar(Pickupable item, int slot)
    {
        hotBarItems[slot] = item;
    }
}

public class InventoryHideShowEventArgs : EventArgs //New event args class for the events called in the InventoryManager class
{
    public InventoryManager.PickupableTypes Type;
    public InventoryHideShowEventArgs(InventoryManager.PickupableTypes type)
    {
        Type = type;
    }
}
