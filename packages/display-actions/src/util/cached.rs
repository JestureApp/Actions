use std::cell::UnsafeCell;

pub struct Cached<T> {
    inner: UnsafeCell<Option<T>>,
}

impl<T> Cached<T> {
    pub fn new() -> Self {
        Self {
            inner: UnsafeCell::new(None),
        }
    }

    fn get(&self) -> Option<&T> {
        unsafe { &*self.inner.get() }.as_ref()
    }

    unsafe fn set(&self, value: T) {
        *self.inner.get() = Some(value);
    }

    pub fn get_or_init<F>(&self, f: F) -> &T
    where
        F: FnOnce() -> T,
    {
        if let Some(value) = self.get() {
            value
        } else {
            let value = f();
            unsafe { self.set(value) };
            self.get().unwrap()
        }
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        use super::*;
        let cached = Cached::new();
        assert_eq!(cached.get_or_init(|| 42), &42);
        assert_eq!(cached.get_or_init(|| 24), &42);
    }
}
