type item = {
  id: int,
  title: string,
  completed: bool,
};

/* State declaration */
type state = {
  count: int,
  show: bool,
  todo: string,
  todolist: list(item),
};

/* Action declaration */
type action =
  | Click
  | Toggle
  | Updatetodo(string)
  | AddTodo(string)
  | ToggleTodo(int);

/**Grab val from event obj */
let valueFromEvent = evt : string => (evt |> ReactEvent.Form.target)##value;

let lastId = ref(0);

let newItem = text => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false};
};

let str = ReasonReact.string;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, _children) => {
    ...component,
    render: (_) =>
      <div className="item" onClick=(_evt => onToggle())>
        <input type_="checkbox" readOnly=true checked=item.completed/>
        (str(item.title))
      </div>,
  };
};

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Todos");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~greeting, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {count: 0, show: true, todo: "", todolist: []},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    | Updatetodo(value) => ReasonReact.Update({...state, todo: value})
    | AddTodo(value) =>
      ReasonReact.Update({
        ...state,
        todolist: [newItem(value), ...state.todolist],
      })
    | ToggleTodo(id) =>
      let items =
        List.map(
          item =>
            item.id === id ? {...item, completed: ! item.completed} : item,
          state.todolist,
        );
      ReasonReact.Update({...state, todolist: items});
    },
  render: self => {
    let message =
      "You've clicked this " ++ string_of_int(self.state.count) ++ " times(s)";
    <div>
      <button onClick=(_event => self.send(Click))>
        (ReasonReact.string(message))
      </button>
      <button onClick=(_event => self.send(Toggle))>
        (ReasonReact.string("Toggle greeting"))
      </button>
      (self.state.show ? ReasonReact.string(greeting) : ReasonReact.null)
      <br />
      <input
        placeholder="Enter todo Item"
        onChange=(event => self.send(Updatetodo(valueFromEvent(event))))
      />
      <button onClick=(_event => self.send(AddTodo(self.state.todo)))>
        (ReasonReact.string("Add Todo"))
      </button>
      <div>
        (
          ReasonReact.array(
            Array.of_list(
              List.map(
                item =>
                  <TodoItem item onToggle=(_ => self.send(ToggleTodo(item.id))) key=(string_of_int(item.id))>
                    (ReasonReact.string(item.title))
                  </TodoItem>,
                self.state.todolist,
              ),
            ),
          )
        )
      </div>
    </div>;
  },
};